#include "../common/headers.p4"
#include "../common/parsers.p4"

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

// sketch block start
primitive_action cms_update_0_0();
action sketch_action() {
    cms_update_0_0();
}
// sketch block end

table sketch_table {
    actions {
        sketch_action;
    }
}

control ingress {
    apply(sketch_table);
    apply(forward);
}

control egress {
}
