import os
import sys
import yaml
import random
import math
import re

MAX_UB = 65535


def make_sub(sub_old, sub_new, file_path):
    with open(file_path, "r") as sources:
        lines = sources.readlines()
    with open(file_path, "w") as sources:
        for line in lines:
            sources.write(
                re.sub(sub_old,
                       sub_new,
                       line)
            )


def implement_manifest_v2(manifest, sketch_dir):
    """
    Not supporting multiple sketches of different types
    Not supporting LB UB
    """
    assert(len(manifest['sketches']) == 1)
    sk = manifest['sketches'][0]
    rows = sk['rows']
    cols = sk['cols']
    # levels = sk['levels']
    file_path = os.path.join(sketch_dir, 'sandbox.c')

    sub_new = '#define NUM_COLS {}'.format(cols)
    sub_old = '#define NUM_COLS [0-9]*'
    make_sub(sub_old, sub_new, file_path)

    sub_new = '#define NUM_ROWS {}'.format(rows)
    sub_old = '#define NUM_ROWS [0-9]*'
    make_sub(sub_old, sub_new, file_path)


def implement_manifest_v1(manifest):
    total_thr = manifest['total_thr'] # aggregate thr for device over all flows
    sandbox_lines = [
        '#include "sandbox.h"\n\n'
    ]
    p4actions = []
    sk_num = 0

    for sk in manifest['sketches']:
        # sk.thr is the portion of all packets relevant to sk
        # different sketches can be updated on the same packet so
        # sum of sk.thr over all sketches can exceed total_thr
        rows = sk['rows']
        cols = sk['cols']
        prob_update = sk['thr'] * sk['frac'] / total_thr
        this_range = math.ceil(prob_update * MAX_UB)
        LB = random.randint(0, MAX_UB - this_range)
        UB = LB + this_range

        # Sandbox
        sandbox_lines.append('#define NUM_COLS_{} {}\n'.format(sk_num, cols))
        sandbox_lines.append('#define NUM_ROWS_{} {}\n\n'.format(sk_num, rows))
        sandbox_lines.append(
            '__declspec(emem export scope(global)) '
            'int32_t sketch_{}[NUM_ROWS_{}][NUM_COLS_{}];\n\n'
            .format(sk_num, sk_num, sk_num))
        for r in range(rows):
            sandbox_lines.append("HASH_FUNC{}({}, NUM_COLS_{})\n"
                                 .format(r, sk_num, sk_num))
            sandbox_lines.append("UPDATE_ROW({}, {}, {}, {})\n"
                                 .format(sk_num, r, LB, UB))
        sandbox_lines.append('\n')

        # P4 file
        p4actions += ["cms_update_{}_{}();".format(sk_num, r)
                   for r in range(rows)]
        sk_num += 1


    with open('cm-sketch/sandbox.c', 'w') as f:
        for line in sandbox_lines:
            f.write(line)


    sketch_block = (["primitive_action {}\n".format(x) for x in p4actions] +
                    ["action sketch_action() {\n"] +
                    ["    {}\n".format(x) for x in p4actions] +
                    ["}\n"])
    p4 = open('cm-sketch/main.p4', 'r')
    lines = p4.readlines()
    p4.close()
    new_lines = []
    sketching = False
    for line in lines:
        if("// sketch block end" in line):
            sketching = False
        if(not sketching):
            new_lines.append(line)
        if("// sketch block start" in line):
            sketching = True
            new_lines.extend(sketch_block)

    new_p4 = open('cm-sketch/main.p4', 'w')
    for line in new_lines:
        new_p4.write(line)
    new_p4.close()


if(__name__ == '__main__'):
    manifest_file = sys.argv[1]
    with open(manifest_file) as f:
        manifest = yaml.safe_load(f)

    if(len(sys.argv) > 2):
        manifest_id = int(sys.argv[2]) - 1
        assert(len(sys.argv) > 3)
        sketch_dir = sys.argv[3]
        implement_manifest_v2(manifest[manifest_id], sketch_dir)
    else:
        implement_manifest_v1(manifest)
