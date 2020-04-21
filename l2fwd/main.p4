#include "common/headers.p4"
#include "common/parsers.p4"

action do_forward(espec) {
    modify_field(standard_metadata.egress_spec, espec);
}

action drop_act() {
    drop();
}

table forward {
    reads {
        standard_metadata.ingress_port : exact;
        tcp.dstPort : exact;
    }
    actions {
        do_forward;
        drop_act;
    }
}

control ingress {
    apply(forward);
}

control egress {
}
