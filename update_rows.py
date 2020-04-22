import sys

rows = int(sys.argv[1])

# Sandbox
sandbox = open('cm-sketch/sandbox.c', 'r')
lines = sandbox.readlines()
sandbox.close()

new_lines = []
for line in lines:
    if (line[:10] != "UPDATE_ROW"):
        new_lines.append(line)

for r in range(rows):
    new_lines.append("UPDATE_ROW({}, {})\n".format(r, r % 3))

new_sandbox = open('cm-sketch/sandbox.c', 'w')
for line in new_lines:
    new_sandbox.write(line)
new_sandbox.close()

# P4 file
p4 = open('cm-sketch/main.p4', 'r')
lines = p4.readlines()
p4.close()

actions = ["cms_update_{}_{}();".format(r, r % 3)
           for r in range(rows)]
sketch_block = (["primitive_action {}\n".format(x) for x in actions] +
                ["action sketch_action() {\n"] +
                ["    {}\n".format(x) for x in actions] +
                ["}\n"])

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
