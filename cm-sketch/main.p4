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
primitive_action cms_update_0_1();
primitive_action cms_update_0_2();
primitive_action cms_update_0_3();
primitive_action cms_update_0_4();
primitive_action cms_update_0_5();
primitive_action cms_update_0_6();
primitive_action cms_update_0_7();
action sketch_action() {
    cms_update_0_0();
    cms_update_0_1();
    cms_update_0_2();
    cms_update_0_3();
    cms_update_0_4();
    cms_update_0_5();
    cms_update_0_6();
    cms_update_0_7();
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
