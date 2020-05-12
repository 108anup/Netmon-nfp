import yaml
from implement_manifest import implement_manifest
import sys
import subprocess
import os
from build_csv import get_rate


def run_experiment(name):
    cwd = os.getcwd()
    run_script = os.path.join(cwd, 'run_experiment.sh')
    with open('run.log', 'w') as f:
        subprocess.call([run_script, '54', name], stdout=f, stderr=f)

    rate = int(get_rate(os.path.join('./runs', name + '.log')))
    # if(rate == -1):
    #    return run_experiment(name)
    return rate


manifests_file = sys.argv[1]
with open(manifests_file) as f:
    manifests = yaml.safe_load(f)


for manifest in manifests:
    # implement_manifest(manifest)
    rate = run_experiment('tmp')
    manifest['ground_truth_ns'] = rate

yaml.dump(manifests, sys.stdout)

