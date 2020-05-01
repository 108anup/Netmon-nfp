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
primitive_action cms_update_1_1();
primitive_action cms_update_2_2();
primitive_action cms_update_3_0();
primitive_action cms_update_4_1();
primitive_action cms_update_5_2();
primitive_action cms_update_6_0();
primitive_action cms_update_7_1();
primitive_action cms_update_8_2();
primitive_action cms_update_9_0();
primitive_action cms_update_10_1();
action sketch_action() {
    cms_update_0_0();
    cms_update_1_1();
    cms_update_2_2();
    cms_update_3_0();
    cms_update_4_1();
    cms_update_5_2();
    cms_update_6_0();
    cms_update_7_1();
    cms_update_8_2();
    cms_update_9_0();
    cms_update_10_1();
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
