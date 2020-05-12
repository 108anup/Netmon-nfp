import yaml

manifest = {
    'sketches': [
        {
            'rows': 4,
            'cols': 32768,
            'thr': 1,
        },
        {
            'rows': 4,
            'cols': 32768,
            'thr': 1,
        }
    ],
    'total_thr': 2
}

with open('manifest.yml', 'w') as f:
    yaml.dump(manifest, f)
