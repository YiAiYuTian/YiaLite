#ifndef YIALITE_FLAG_MACROS_H
#define YIALITE_FLAG_MACROS_H

#define GEN_FLAG_BIN_OP(op, flag_enum, flag_raw, conv_fun)                          \
    inline constexpr flag_raw operator op(flag_enum a, flag_enum b)                 \
    {                                                                               \
        return conv_fun(a) op conv_fun(b);                                          \
    }                                                                               \
    inline constexpr flag_raw operator op(flag_raw a, flag_enum b)                  \
    {                                                                               \
        return a op conv_fun(b);                                                    \
    }                                                                               \
    inline constexpr flag_raw operator op(flag_enum a, flag_raw b)                  \
    {                                                                               \
        return conv_fun(a) op b;                                                    \
    }

#define GEN_FLAG_ASSIGN_OP(op, flag_enum, flag_raw, conv_fun)                       \
    inline constexpr flag_raw& operator op##=(flag_raw& lhs, flag_enum rhs)         \
    {                                                                               \
        lhs op##= conv_fun(rhs);                                                    \
        return lhs;                                                                 \
    }

#define GEN_FLAG_BIN_OP_AND_ASSIGN_OP(op, flag_enum, flag_raw, conv_fun)            \
    GEN_FLAG_BIN_OP(op, flag_enum, flag_raw, conv_fun)                              \
    GEN_FLAG_ASSIGN_OP(op, flag_enum, flag_raw, conv_fun)

#endif