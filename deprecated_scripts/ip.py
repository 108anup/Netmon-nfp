import socket, struct
import operator

def ip2long(ip):
    """
    Convert an IP string to long
    """
    packedIP = socket.inet_aton(ip)
    return struct.unpack("!L", packedIP)[0]

src_ip_list = ["192.123.4.13", "192.123.4.13", "192.123.4.19", "192.123.4.61",
           "192.111.1.2", "192.121.1.2", "192.131.1.2", "192.141.18.61",
           "192.151.19.61", "192.161.1.41", "192.171.1.61", "192.181.1.13",
           "176.251.17.31", "192.101.1.4", "176.39.23.81", "176.39.13.89"
]

dst_ip_list = ["172.16.13.35", "172.16.19.36", "172.16.17.37", "172.16.29.33"]

idxs = [set(), set(), set()]
ops = [operator.__and__, operator.__xor__, operator.__or__]
for i in range(len(idxs)):
    for sip_idx in range(len(src_ip_list)):
        sip = src_ip_list[sip_idx]
        dip = dst_ip_list[sip_idx % 4]
        key = ops[i](ip2long(sip), ip2long(dip)) % 3072
        if key in idxs[i]:
            print(sip)
        idxs[i].add(key)

# for i in range(len(idxs)):
#     print(len(idxs[i]))

for i in range(len(src_ip_list)):
    print("sequence {} 0 0000:0000:0000 f452:140f:4740 {} {}/24 1234 1000 ipv4 tcp 1 64".format(
        i, src_ip_list[i], dst_ip_list[i%4]))
