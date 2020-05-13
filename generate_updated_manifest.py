import yaml
import sys
import os
from build_csv import get_rate


# def run_experiment(name):
#     cwd = os.getcwd()
#     run_script = os.path.join(cwd, 'run_experiment.sh')
#     with open('run.log', 'w') as f:
#         subprocess.call([run_script, '54', name], stdout=f, stderr=f)

#     rate = int(get_rate(os.path.join('./runs', name + '.log')))
#     # if(rate == -1):
#     #    return run_experiment(name)
#     return rate


manifests_file = sys.argv[1]
with open(manifests_file) as f:
    manifests = yaml.safe_load(f)
manifests_file_name = os.path.basename(manifests_file)[:-4]
ground_truth_path = os.path.join('./runs', manifests_file_name)

idx = 1
for num, manifest in enumerate(manifests):
    # print("{}: ".format(idx), end="")
    try:
        name = manifests_file_name + "_{}.log".format(num+1)
        rate = int(get_rate(os.path.join(ground_truth_path, name)))
        manifest['ground_truth_ns'] = rate

        # CSV print for modeling
        print("{}, {}, {}".format(manifest['sketches'][0]['rows'],
                                  manifest['sketches'][0]['cols'],
                                  manifest['ground_truth_ns']))
    except:
        pass
    idx += 1
# yaml.dump(manifests, sys.stdout)

