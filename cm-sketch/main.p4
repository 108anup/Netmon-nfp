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

primitive_action cms_update0();
primitive_action cms_update1();
primitive_action cms_update2();
action sketch_action() {
    cms_update0();
    cms_update1();
    cms_update2();
}

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
