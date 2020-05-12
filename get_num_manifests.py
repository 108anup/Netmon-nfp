import yaml
import sys

manifests_file = sys.argv[1]
with open(manifests_file) as f:
    manifests = yaml.safe_load(f)

print(len(manifests))
