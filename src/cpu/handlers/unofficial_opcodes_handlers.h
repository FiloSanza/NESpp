#ifndef NESPP_UNOFFICIAL_OPCODES_HANDLERS_H
#define NESPP_UNOFFICIAL_OPCODES_HANDLERS_H

#include <map>
#include <functional>
#include "opcodes.h"
#include "../cpu.h"
#include "transfer_opcodes_handlers.h"
#include "store_opcodes_handlers.h"
#include "flag_opcodes_handlers.h"
#include "bitwise_opcodes_handlers.h"
#include "branch_opcodes_handlers.h"
#include "stack_opcodes_handlers.h"
#include "compare_opcodes_handlers.h"
#include "math_opcodes_handlers.h"
#include "load_opcodes_handlers.h"
#include "jump_opcodes_handlers.h"
#include "system_opcode_handlers.h"

namespace nespp::unofficial_opcodes {
    /*
    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers();

    void kil(Cpu &cpu);

    void nop(Cpu &cpu);

    void anc_immediate(Cpu &cpu);

    void alr_immediate(Cpu &cpu);

    void arr_immediate(Cpu &cpu);

    void slo_zero(Cpu &cpu);
    void slo_zero_x(Cpu &cpu);
    void slo_absolute(Cpu &cpu);
    void slo_absolute_x(Cpu &cpu);
    void slo_absolute_y(Cpu &cpu);
    void slo_indirect_x(Cpu &cpu);
    void slo_indirect_y(Cpu &cpu);

    void rla_zero(Cpu &cpu);
    void rla_zero_x(Cpu &cpu);
    void rla_absolute(Cpu &cpu);
    void rla_absolute_x(Cpu &cpu);
    void rla_absolute_y(Cpu &cpu);
    void rla_indirect_x(Cpu &cpu);
    void rla_indirect_y(Cpu &cpu);

    void sre_zero(Cpu &cpu);
    void sre_zero_x(Cpu &cpu);
    void sre_absolute(Cpu &cpu);
    void sre_absolute_x(Cpu &cpu);
    void sre_absolute_y(Cpu &cpu);
    void sre_indirect_x(Cpu &cpu);
    void sre_indirect_y(Cpu &cpu);

    void rra_zero(Cpu &cpu);
    void rra_zero_x(Cpu &cpu);
    void rra_absolute(Cpu &cpu);
    void rra_absolute_x(Cpu &cpu);
    void rra_absolute_y(Cpu &cpu);
    void rra_indirect_x(Cpu &cpu);
    void rra_indirect_y(Cpu &cpu);

    void sax_zero(Cpu &cpu);
    void sax_zero_y(Cpu &cpu);
    void sax_abs(Cpu &cpu);
    void sax_ind_x(Cpu &cpu);

    void ahx_abs_y(Cpu &cpu);
    void ahx_ind_y(Cpu &cpu);

    void lax_immediate(Cpu &cpu);
    void lax_zero(Cpu &cpu);
    void lax_zero_y(Cpu &cpu);
    void lax_absolute(Cpu &cpu);
    void lax_absolute_y(Cpu &cpu);
    void lax_indirect_x(Cpu &cpu);
    void lax_indirect_y(Cpu &cpu);

    void dcp_zero(Cpu &cpu);
    void dcp_zero_x(Cpu &cpu);
    void dcp_absolute(Cpu &cpu);
    void dcp_absolute_x(Cpu &cpu);
    void dcp_absolute_y(Cpu &cpu);
    void dcp_indirect_x(Cpu &cpu);
    void dcp_indirect_y(Cpu &cpu);

    void isc_zero(Cpu &cpu);
    void isc_zero_x(Cpu &cpu);
    void isc_absolute(Cpu &cpu);
    void isc_absolute_x(Cpu &cpu);
    void isc_absolute_y(Cpu &cpu);
    void isc_indirect_x(Cpu &cpu);
    void isc_indirect_y(Cpu &cpu);

    void xaa_immediate(Cpu &cpu);

    void axs_immediate(Cpu &cpu);

    void sbc_immediate(Cpu &cpu);

    void tas_absolute_y(Cpu &cpu);

    void las_absolute_y(Cpu &cpu);

    void shy_absolute_x(Cpu &cpu);
    void shx_absolute_y(Cpu &cpu);
*/
}

#endif //NESPP_UNOFFICIAL_OPCODES_HANDLERS_H
