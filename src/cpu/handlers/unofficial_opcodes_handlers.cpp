#include "unofficial_opcodes_handlers.h"

namespace nespp::unofficial_opcodes {
    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers() {
        auto handlers = std::map<uint8_t, std::function<void(Cpu &)>>();

        handlers.emplace(UnofficialOpcodes::KIL_1, kil);
        handlers.emplace(UnofficialOpcodes::KIL_2, kil);
        handlers.emplace(UnofficialOpcodes::KIL_3, kil);
        handlers.emplace(UnofficialOpcodes::KIL_4, kil);
        handlers.emplace(UnofficialOpcodes::KIL_5, kil);
        handlers.emplace(UnofficialOpcodes::KIL_6, kil);
        handlers.emplace(UnofficialOpcodes::KIL_7, kil);
        handlers.emplace(UnofficialOpcodes::KIL_8, kil);
        handlers.emplace(UnofficialOpcodes::KIL_9, kil);
        handlers.emplace(UnofficialOpcodes::KIL_10, kil);
        handlers.emplace(UnofficialOpcodes::KIL_11, kil);
        handlers.emplace(UnofficialOpcodes::KIL_12, kil);
        handlers.emplace(UnofficialOpcodes::NOP_1, nop);
        handlers.emplace(UnofficialOpcodes::NOP_2, nop);
        handlers.emplace(UnofficialOpcodes::NOP_3, nop);
        handlers.emplace(UnofficialOpcodes::NOP_4, nop);
        handlers.emplace(UnofficialOpcodes::NOP_5, nop);
        handlers.emplace(UnofficialOpcodes::NOP_6, nop);
        handlers.emplace(UnofficialOpcodes::NOP_7, nop);
        handlers.emplace(UnofficialOpcodes::NOP_8, nop);
        handlers.emplace(UnofficialOpcodes::NOP_9, nop);
        handlers.emplace(UnofficialOpcodes::NOP_10, nop);
        handlers.emplace(UnofficialOpcodes::NOP_11, nop);
        handlers.emplace(UnofficialOpcodes::NOP_12, nop);
        handlers.emplace(UnofficialOpcodes::NOP_13, nop);
        handlers.emplace(UnofficialOpcodes::NOP_14, nop);
        handlers.emplace(UnofficialOpcodes::NOP_15, nop);
        handlers.emplace(UnofficialOpcodes::NOP_16, nop);
        handlers.emplace(UnofficialOpcodes::NOP_17, nop);
        handlers.emplace(UnofficialOpcodes::NOP_18, nop);
        handlers.emplace(UnofficialOpcodes::NOP_19, nop);
        handlers.emplace(UnofficialOpcodes::NOP_20, nop);
        handlers.emplace(UnofficialOpcodes::NOP_21, nop);
        handlers.emplace(UnofficialOpcodes::NOP_22, nop);
        handlers.emplace(UnofficialOpcodes::NOP_23, nop);
        handlers.emplace(UnofficialOpcodes::NOP_24, nop);
        handlers.emplace(UnofficialOpcodes::NOP_25, nop);
        handlers.emplace(UnofficialOpcodes::NOP_26, nop);
        handlers.emplace(UnofficialOpcodes::NOP_27, nop);
        handlers.emplace(UnofficialOpcodes::NOP_28, nop);
        handlers.emplace(UnofficialOpcodes::ANC_IMM_1, anc_immediate);
        handlers.emplace(UnofficialOpcodes::ANC_IMM_2, anc_immediate);
        handlers.emplace(UnofficialOpcodes::ALR_IMM, alr_immediate);
        handlers.emplace(UnofficialOpcodes::ARR_IMM, arr_immediate);
        handlers.emplace(UnofficialOpcodes::SLO_ZERO, slo_zero);
        handlers.emplace(UnofficialOpcodes::SLO_ZERO_X, slo_zero_x);
        handlers.emplace(UnofficialOpcodes::SLO_ABS, slo_absolute);
        handlers.emplace(UnofficialOpcodes::SLO_ABS_X, slo_absolute_x);
        handlers.emplace(UnofficialOpcodes::SLO_ABS_Y, slo_absolute_y);
        handlers.emplace(UnofficialOpcodes::SLO_IND_X, slo_indirect_x);
        handlers.emplace(UnofficialOpcodes::SLO_IND_Y, slo_indirect_y);
        handlers.emplace(UnofficialOpcodes::RLA_ZERO, rla_zero);
        handlers.emplace(UnofficialOpcodes::RLA_ZER_X, rla_zero_x);
        handlers.emplace(UnofficialOpcodes::RLA_ABS, rla_absolute);
        handlers.emplace(UnofficialOpcodes::RLA_ABS_X, rla_absolute_x);
        handlers.emplace(UnofficialOpcodes::RLA_ABS_Y, rla_absolute_y);
        handlers.emplace(UnofficialOpcodes::RLA_IND_X, rla_indirect_x);
        handlers.emplace(UnofficialOpcodes::RLA_IND_Y, rla_indirect_y);
        handlers.emplace(UnofficialOpcodes::SRE_ZERO, sre_zero);
        handlers.emplace(UnofficialOpcodes::SRE_ZERO_X, sre_zero_x);
        handlers.emplace(UnofficialOpcodes::SRE_ABS, sre_absolute);
        handlers.emplace(UnofficialOpcodes::SRE_ABS_X, sre_absolute_x);
        handlers.emplace(UnofficialOpcodes::SRE_ABS_Y, sre_absolute_y);
        handlers.emplace(UnofficialOpcodes::SRE_IND_X, sre_indirect_x);
        handlers.emplace(UnofficialOpcodes::SRE_IND_Y, sre_indirect_y);
        handlers.emplace(UnofficialOpcodes::RRA_ZERO, rra_zero);
        handlers.emplace(UnofficialOpcodes::RRA_ZERO_X, rra_zero_x);
        handlers.emplace(UnofficialOpcodes::RRA_ABS, rra_absolute);
        handlers.emplace(UnofficialOpcodes::RRA_ABS_X, rra_absolute_x);
        handlers.emplace(UnofficialOpcodes::RRA_ABS_Y, rra_absolute_y);
        handlers.emplace(UnofficialOpcodes::RRA_IND_X, rra_indirect_x);
        handlers.emplace(UnofficialOpcodes::RRA_IND_Y, rra_indirect_y);
        handlers.emplace(UnofficialOpcodes::SAX_ZERO, sax_zero);
        handlers.emplace(UnofficialOpcodes::SAX_ZERO_Y, sax_zero_y);
        handlers.emplace(UnofficialOpcodes::SAX_ABS, sax_abs);
        handlers.emplace(UnofficialOpcodes::SAX_IND_X, sax_ind_x);
        handlers.emplace(UnofficialOpcodes::AHX_ABS_Y, ahx_abs_y);
        handlers.emplace(UnofficialOpcodes::AHX_IND_Y, ahx_ind_y);
        handlers.emplace(UnofficialOpcodes::LAX_IMM, lax_immediate);
        handlers.emplace(UnofficialOpcodes::LAX_ZERO, lax_zero);
        handlers.emplace(UnofficialOpcodes::LAX_ZERO_Y, lax_zero_y);
        handlers.emplace(UnofficialOpcodes::LAX_ABS, lax_absolute);
        handlers.emplace(UnofficialOpcodes::LAX_ABS_Y, lax_absolute_y);
        handlers.emplace(UnofficialOpcodes::LAX_IND_X, lax_indirect_x);
        handlers.emplace(UnofficialOpcodes::LAX_IND_Y, lax_indirect_y);
        handlers.emplace(UnofficialOpcodes::DCP_ZERO, dcp_zero);
        handlers.emplace(UnofficialOpcodes::DCP_ZERO_X, dcp_zero_x);
        handlers.emplace(UnofficialOpcodes::DCP_ABS, dcp_absolute);
        handlers.emplace(UnofficialOpcodes::DCP_ABS_X, dcp_absolute_x);
        handlers.emplace(UnofficialOpcodes::DCP_ABS_Y, dcp_absolute_y);
        handlers.emplace(UnofficialOpcodes::DCP_IND_X, dcp_indirect_x);
        handlers.emplace(UnofficialOpcodes::DCP_IND_Y, dcp_indirect_y);
        handlers.emplace(UnofficialOpcodes::ISC_ZERO, isc_zero);
        handlers.emplace(UnofficialOpcodes::ISC_ZERO_X, isc_zero_x);
        handlers.emplace(UnofficialOpcodes::ISC_ABS, isc_absolute);
        handlers.emplace(UnofficialOpcodes::ISC_ABS_X, isc_absolute_x);
        handlers.emplace(UnofficialOpcodes::ISC_ABS_Y, isc_absolute_y);
        handlers.emplace(UnofficialOpcodes::ISC_IND_X, isc_indirect_x);
        handlers.emplace(UnofficialOpcodes::ISC_IND_Y, isc_indirect_y);
        handlers.emplace(UnofficialOpcodes::XAA_IMM, xaa_immediate);
        handlers.emplace(UnofficialOpcodes::TAS_ABS_Y, tas_absolute_y);
        handlers.emplace(UnofficialOpcodes::LAS_ABS_Y, las_absolute_y);
        handlers.emplace(UnofficialOpcodes::AXS_IMM, axs_immediate);
        handlers.emplace(UnofficialOpcodes::SBC_IMM_ILL, sbc_immediate);
        handlers.emplace(UnofficialOpcodes::SHY_ABS_X, shy_absolute_x);
        handlers.emplace(UnofficialOpcodes::SHX_ABS_Y, shx_absolute_y);

        return handlers;
    }

    void kil(Cpu &cpu) {

    }

    void nop(Cpu &cpu) {

    }

    void anc_immediate(Cpu &cpu) {

    }

    void alr_immediate(Cpu &cpu) {

    }

    void arr_immediate(Cpu &cpu) {

    }

    void slo_zero(Cpu &cpu) {

    }

    void slo_zero_x(Cpu &cpu) {

    }

    void slo_absolute(Cpu &cpu) {

    }

    void slo_absolute_x(Cpu &cpu) {

    }

    void slo_absolute_y(Cpu &cpu) {

    }

    void slo_indirect_x(Cpu &cpu) {

    }

    void slo_indirect_y(Cpu &cpu) {

    }

    void rla_zero(Cpu &cpu) {

    }

    void rla_zero_x(Cpu &cpu) {

    }

    void rla_absolute(Cpu &cpu) {

    }

    void rla_absolute_x(Cpu &cpu) {

    }

    void rla_absolute_y(Cpu &cpu) {

    }

    void rla_indirect_x(Cpu &cpu) {

    }

    void rla_indirect_y(Cpu &cpu) {

    }

    void sre_zero(Cpu &cpu) {

    }

    void sre_zero_x(Cpu &cpu) {

    }

    void sre_absolute(Cpu &cpu) {

    }

    void sre_absolute_x(Cpu &cpu) {

    }

    void sre_absolute_y(Cpu &cpu) {

    }

    void sre_indirect_x(Cpu &cpu) {

    }

    void sre_indirect_y(Cpu &cpu) {

    }

    void rra_zero(Cpu &cpu) {

    }

    void rra_zero_x(Cpu &cpu) {

    }

    void rra_absolute(Cpu &cpu) {

    }

    void rra_absolute_x(Cpu &cpu) {

    }

    void rra_absolute_y(Cpu &cpu) {

    }

    void rra_indirect_x(Cpu &cpu) {

    }

    void rra_indirect_y(Cpu &cpu) {

    }

    void sax_zero(Cpu &cpu) {

    }

    void sax_zero_y(Cpu &cpu) {

    }

    void sax_abs(Cpu &cpu) {

    }

    void sax_ind_x(Cpu &cpu) {

    }

    void ahx_abs_y(Cpu &cpu) {

    }

    void ahx_ind_y(Cpu &cpu) {

    }

    void lax_immediate(Cpu &cpu) {

    }

    void lax_zero(Cpu &cpu) {

    }

    void lax_zero_y(Cpu &cpu) {

    }

    void lax_absolute(Cpu &cpu) {

    }

    void lax_absolute_y(Cpu &cpu) {

    }

    void lax_indirect_x(Cpu &cpu) {

    }

    void lax_indirect_y(Cpu &cpu) {

    }

    void dcp_zero(Cpu &cpu) {

    }

    void dcp_zero_x(Cpu &cpu) {

    }

    void dcp_absolute(Cpu &cpu) {

    }

    void dcp_absolute_x(Cpu &cpu) {

    }

    void dcp_absolute_y(Cpu &cpu) {

    }

    void dcp_indirect_x(Cpu &cpu) {

    }

    void dcp_indirect_y(Cpu &cpu) {

    }

    void isc_zero(Cpu &cpu) {

    }

    void isc_zero_x(Cpu &cpu) {

    }

    void isc_absolute(Cpu &cpu) {

    }

    void isc_absolute_x(Cpu &cpu) {

    }

    void isc_absolute_y(Cpu &cpu) {

    }

    void isc_indirect_x(Cpu &cpu) {

    }

    void isc_indirect_y(Cpu &cpu) {

    }

    void xaa_immediate(Cpu &cpu) {

    }

    void axs_immediate(Cpu &cpu) {

    }

    void sbc_immediate(Cpu &cpu) {

    }

    void tas_absolute_y(Cpu &cpu) {

    }

    void las_absolute_y(Cpu &cpu) {

    }

    void shy_absolute_x(Cpu &cpu) {

    }

    void shx_absolute_y(Cpu &cpu) {

    }
/*


    void kil(Cpu &cpu) {
        throw std::runtime_error("KIL OPCODE");
    }

    void nop(Cpu &cpu) {
        system_opcodes::nop(cpu);
    }

    void anc_immediate(Cpu &cpu) {
        auto value = cpu.get_u8();
        bitwise_opcodes::bitwise_and(cpu, cpu.get_a(), value);
        cpu.get_program_status().set_carry(bits::get_nth_bit(value, 7));
    }

    void alr_immediate(Cpu &cpu) {
        bitwise_opcodes::and_immediate(cpu);
        bitwise_opcodes::lsr_accumulator(cpu);
    }

    void arr_immediate(Cpu &cpu) {
        bitwise_opcodes::and_immediate(cpu);
        bitwise_opcodes::ror_acc(cpu);
    }

    void slo_zero(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::asl_zero(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::ora_zero(cpu);
    }

    void slo_zero_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::asl_zero_x(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::ora_zero_x(cpu);
    }

    void slo_absolute(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::asl_absolute(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::ora_absolute(cpu);
    }

    void slo_absolute_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::asl_absolute_x(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::ora_absolute_x(cpu);
    }

    void slo_absolute_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::asl_absolute_y(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::ora_absolute_y(cpu);
    }

    void slo_indirect_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::asl_indirect_x(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::ora_indirect_x(cpu);
    }

    void slo_indirect_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::asl_indirect_y(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::ora_indirect_y(cpu);
    }

    void rla_zero(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::rol_zero(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::and_zero(cpu);
    }

    void rla_zero_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::rol_zero_x(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::and_zero_x(cpu);
    }

    void rla_absolute(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::rol_abs(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::and_absolute(cpu);
    }

    void rla_absolute_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::rol_abs_x(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::and_absolute_x(cpu);
    }

    void rla_absolute_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::rol_abs_y(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::and_absolute_y(cpu);
    }

    void rla_indirect_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::rol_ind_x(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::and_indirect_x(cpu);
    }

    void rla_indirect_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::rol_ind_y(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::and_indirect_y(cpu);
    }

    void sre_zero(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::lsr_zero(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::eor_zero(cpu);
    }

    void sre_zero_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::lsr_zero_x(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::eor_zero_x(cpu);
    }

    void sre_absolute(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::lsr_absolute(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::eor_absolute(cpu);
    }

    void sre_absolute_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::lsr_absolute_x(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::eor_absolute_x(cpu);
    }

    void sre_absolute_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::lsr_absolute_y(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::eor_absolute_y(cpu);
    }

    void sre_indirect_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::lsr_indirect_x(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::eor_indirect_x(cpu);
    }

    void sre_indirect_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::lsr_indirect_y(cpu);
        cpu.get_program_counter().set_value(pc);
        bitwise_opcodes::eor_indirect_y(cpu);
    }

    void rra_zero(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::ror_zero(cpu);
        cpu.get_program_counter().set_value(pc);
        math_opcodes::adc_zero(cpu);
    }

    void rra_zero_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::ror_zero_x(cpu);
        cpu.get_program_counter().set_value(pc);
        math_opcodes::adc_zero_x(cpu);
    }

    void rra_absolute(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::ror_abs(cpu);
        cpu.get_program_counter().set_value(pc);
        math_opcodes::adc_absolute(cpu);
    }

    void rra_absolute_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::ror_abs_x(cpu);
        cpu.get_program_counter().set_value(pc);
        math_opcodes::adc_absolute_x(cpu);
    }

    void rra_absolute_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::ror_abs_y(cpu);
        cpu.get_program_counter().set_value(pc);
        math_opcodes::adc_absolute_y(cpu);
    }

    void rra_indirect_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::ror_ind_x(cpu);
        cpu.get_program_counter().set_value(pc);
        math_opcodes::adc_indirect_x(cpu);
    }

    void rra_indirect_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        bitwise_opcodes::ror_ind_y(cpu);
        cpu.get_program_counter().set_value(pc);
        math_opcodes::adc_indirect_y(cpu);
    }

    void sax_zero(Cpu &cpu) {
        auto value = cpu.get_a().get_value() & cpu.get_x().get_value();
        store_opcodes::store(cpu, value, cpu.get_u8());
    }

    void sax_zero_y(Cpu &cpu) {
        auto value = cpu.get_a().get_value() & cpu.get_x().get_value();
        store_opcodes::store(cpu, value, cpu.get_zero_y_address());
    }

    void sax_abs(Cpu &cpu) {
        auto value = cpu.get_a().get_value() & cpu.get_x().get_value();
        store_opcodes::store(cpu, value, cpu.get_u16());
    }

    void sax_ind_x(Cpu &cpu) {
        auto value = cpu.get_a().get_value() & cpu.get_x().get_value();
        store_opcodes::store(cpu, value, cpu.get_indirect_x_address());
    }

    void ahx_abs_y(Cpu &cpu) {

    }

    void ahx_ind_y(Cpu &cpu) {

    }

    void lax_immediate(Cpu &cpu) {
        load_opcodes::lda_immediate(cpu);
        transfer_opcodes::tax(cpu);
    }

    void lax_zero(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        load_opcodes::lda_zero(cpu);
        cpu.get_program_counter().set_value(pc);
        load_opcodes::ldx_zero(cpu);
    }

    void lax_zero_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        load_opcodes::lda_zero_y(cpu);
        cpu.get_program_counter().set_value(pc);
        load_opcodes::ldx_zero_y(cpu);
    }

    void lax_absolute(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        load_opcodes::lda_absolute(cpu);
        cpu.get_program_counter().set_value(pc);
        load_opcodes::ldx_absolute(cpu);
    }

    void lax_absolute_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        load_opcodes::lda_absolute_y(cpu);
        cpu.get_program_counter().set_value(pc);
        load_opcodes::ldx_absolute_y(cpu);
    }

    void lax_indirect_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        load_opcodes::lda_indirect_x(cpu);
        cpu.get_program_counter().set_value(pc);
        load_opcodes::ldx_indirect_x(cpu);
    }

    void lax_indirect_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        load_opcodes::lda_indirect_y(cpu);
        cpu.get_program_counter().set_value(pc);
        load_opcodes::ldx_indirect_y(cpu);
    }

    void dcp_zero(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        math_opcodes::dec_zero(cpu);
        cpu.get_program_counter().set_value(pc);
        compare_opcodes::cmp_zero(cpu);
    }

    void dcp_zero_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        math_opcodes::dec_zero_x(cpu);
        cpu.get_program_counter().set_value(pc);
        compare_opcodes::cmp_zero_x(cpu);
    }

    void dcp_absolute(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        math_opcodes::dec_abs(cpu);
        cpu.get_program_counter().set_value(pc);
        compare_opcodes::cmp_abs(cpu);
    }

    void dcp_absolute_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        math_opcodes::dec_abs_x(cpu);
        cpu.get_program_counter().set_value(pc);
        compare_opcodes::cmp_abs_x(cpu);
    }

    void dcp_absolute_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        math_opcodes::dec_abs_y(cpu);
        cpu.get_program_counter().set_value(pc);
        compare_opcodes::cmp_abs_y(cpu);
    }

    void dcp_indirect_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        math_opcodes::dec_indirect_x(cpu);
        cpu.get_program_counter().set_value(pc);
        compare_opcodes::cmp_ind_x(cpu);
    }

    void dcp_indirect_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        math_opcodes::dec_indirect_y(cpu);
        cpu.get_program_counter().set_value(pc);
        compare_opcodes::cmp_ind_y(cpu);
    }

    void isc_zero(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        math_opcodes::inc_zero(cpu);
        cpu.get_program_counter().set_value(pc);
        math_opcodes::sbc_zero(cpu);
    }

    void isc_zero_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        math_opcodes::inc_zero_x(cpu);
        cpu.get_program_counter().set_value(pc);
        math_opcodes::sbc_zero_x(cpu);
    }

    void isc_absolute(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        math_opcodes::inc_abs(cpu);
        cpu.get_program_counter().set_value(pc);
        math_opcodes::sbc_absolute(cpu);
    }

    void isc_absolute_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        math_opcodes::inc_abs_x(cpu);
        cpu.get_program_counter().set_value(pc);
        math_opcodes::sbc_absolute_x(cpu);
    }

    void isc_absolute_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        math_opcodes::inc_abs_y(cpu);
        cpu.get_program_counter().set_value(pc);
        math_opcodes::sbc_absolute_y(cpu);
    }

    void isc_indirect_x(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        math_opcodes::inc_indirect_x(cpu);
        cpu.get_program_counter().set_value(pc);
        math_opcodes::sbc_indirect_x(cpu);
    }

    void isc_indirect_y(Cpu &cpu) {
        auto pc = cpu.get_program_counter().get_value();
        math_opcodes::inc_indirect_y(cpu);
        cpu.get_program_counter().set_value(pc);
        math_opcodes::sbc_indirect_y(cpu);
    }

    void xaa_immediate(Cpu &cpu) {
        transfer_opcodes::txa(cpu);
        bitwise_opcodes::and_immediate(cpu);
    }

    void axs_immediate(Cpu &cpu) {
        auto immediate_val = cpu.get_u8();
        auto result = cpu.get_x().get_value() & cpu.get_a().get_value() - immediate_val;
        cpu.get_x().set_value(result);

        cpu.get_program_status().set_carry(bits::get_nth_bit(result, ));
    }

    void sbc_immediate(Cpu &cpu) {
        math_opcodes::sbc_immediate(cpu);
        system_opcodes::nop(cpu);
    }

    void tas_absolute_y(Cpu &cpu) {

    }

    void las_absolute_y(Cpu &cpu) {

    }

    void shy_absolute_x(Cpu &cpu) {

    }

    void shx_absolute_y(Cpu &cpu) {

    }
*/
}