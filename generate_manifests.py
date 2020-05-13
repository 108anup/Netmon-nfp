import yaml
import sys
# A proper manifest would have flow filters instead of thr
manifest = {
    'sketches': [
        {
            'rows': 4,
            'cols': 32768,
            'thr': 1,
            'frac': 1
        },
        {
            'rows': 4,
            'cols': 32768,
            'thr': 1,
            'frac': 1
        }
    ],
    'total_thr': 2
}

hash_bench = [
    {
        'sketches': [
            {
                'rows': r,
                'cols': 4,
                'thr': 1,
                'frac': 1
            }
        ],
        'total_thr': 1
    }
    for r in range(1, 13)
]

mem_bench = [
    {
        'sketches': [
            {
                'rows': r,
                'cols': 2**logc,
                'thr': 1,
                'frac': 1
            }
        ],
        'total_thr': 1
    }
    for r in [10, 12]
    for logc in range(23)
]

ground_truth = [
    {
        'sketches': [
            {
                'rows': r,
                'cols': 4**logc,
                'thr': 1,
                'frac': 1
            }
        ],
        'total_thr': 1
    }
    for r in range(2, 10, 2)
    for logc in range(2, 12)
]

# double_sketches = {
# }

yaml.dump(ground_truth, sys.stdout)
