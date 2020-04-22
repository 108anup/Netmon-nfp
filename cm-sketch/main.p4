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
primitive_action cms_update_11_2();
primitive_action cms_update_12_0();
primitive_action cms_update_13_1();
primitive_action cms_update_14_2();
primitive_action cms_update_15_0();
primitive_action cms_update_16_1();
primitive_action cms_update_17_2();
primitive_action cms_update_18_0();
primitive_action cms_update_19_1();
primitive_action cms_update_20_2();
primitive_action cms_update_21_0();
primitive_action cms_update_22_1();
primitive_action cms_update_23_2();
primitive_action cms_update_24_0();
primitive_action cms_update_25_1();
primitive_action cms_update_26_2();
primitive_action cms_update_27_0();
primitive_action cms_update_28_1();
primitive_action cms_update_29_2();
primitive_action cms_update_30_0();
primitive_action cms_update_31_1();
primitive_action cms_update_32_2();
primitive_action cms_update_33_0();
primitive_action cms_update_34_1();
primitive_action cms_update_35_2();
primitive_action cms_update_36_0();
primitive_action cms_update_37_1();
primitive_action cms_update_38_2();
primitive_action cms_update_39_0();
primitive_action cms_update_40_1();
primitive_action cms_update_41_2();
primitive_action cms_update_42_0();
primitive_action cms_update_43_1();
primitive_action cms_update_44_2();
primitive_action cms_update_45_0();
primitive_action cms_update_46_1();
primitive_action cms_update_47_2();
primitive_action cms_update_48_0();
primitive_action cms_update_49_1();
primitive_action cms_update_50_2();
primitive_action cms_update_51_0();
primitive_action cms_update_52_1();
primitive_action cms_update_53_2();
primitive_action cms_update_54_0();
primitive_action cms_update_55_1();
primitive_action cms_update_56_2();
primitive_action cms_update_57_0();
primitive_action cms_update_58_1();
primitive_action cms_update_59_2();
primitive_action cms_update_60_0();
primitive_action cms_update_61_1();
primitive_action cms_update_62_2();
primitive_action cms_update_63_0();
primitive_action cms_update_64_1();
primitive_action cms_update_65_2();
primitive_action cms_update_66_0();
primitive_action cms_update_67_1();
primitive_action cms_update_68_2();
primitive_action cms_update_69_0();
primitive_action cms_update_70_1();
primitive_action cms_update_71_2();
primitive_action cms_update_72_0();
primitive_action cms_update_73_1();
primitive_action cms_update_74_2();
primitive_action cms_update_75_0();
primitive_action cms_update_76_1();
primitive_action cms_update_77_2();
primitive_action cms_update_78_0();
primitive_action cms_update_79_1();
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
    cms_update_11_2();
    cms_update_12_0();
    cms_update_13_1();
    cms_update_14_2();
    cms_update_15_0();
    cms_update_16_1();
    cms_update_17_2();
    cms_update_18_0();
    cms_update_19_1();
    cms_update_20_2();
    cms_update_21_0();
    cms_update_22_1();
    cms_update_23_2();
    cms_update_24_0();
    cms_update_25_1();
    cms_update_26_2();
    cms_update_27_0();
    cms_update_28_1();
    cms_update_29_2();
    cms_update_30_0();
    cms_update_31_1();
    cms_update_32_2();
    cms_update_33_0();
    cms_update_34_1();
    cms_update_35_2();
    cms_update_36_0();
    cms_update_37_1();
    cms_update_38_2();
    cms_update_39_0();
    cms_update_40_1();
    cms_update_41_2();
    cms_update_42_0();
    cms_update_43_1();
    cms_update_44_2();
    cms_update_45_0();
    cms_update_46_1();
    cms_update_47_2();
    cms_update_48_0();
    cms_update_49_1();
    cms_update_50_2();
    cms_update_51_0();
    cms_update_52_1();
    cms_update_53_2();
    cms_update_54_0();
    cms_update_55_1();
    cms_update_56_2();
    cms_update_57_0();
    cms_update_58_1();
    cms_update_59_2();
    cms_update_60_0();
    cms_update_61_1();
    cms_update_62_2();
    cms_update_63_0();
    cms_update_64_1();
    cms_update_65_2();
    cms_update_66_0();
    cms_update_67_1();
    cms_update_68_2();
    cms_update_69_0();
    cms_update_70_1();
    cms_update_71_2();
    cms_update_72_0();
    cms_update_73_1();
    cms_update_74_2();
    cms_update_75_0();
    cms_update_76_1();
    cms_update_77_2();
    cms_update_78_0();
    cms_update_79_1();
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
