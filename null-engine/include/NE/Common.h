#pragma once

#define NE_CONCAT_DETAIL(expr1, expr2) expr1##expr2
#define NE_CONCAT(expr1, expr2) NE_CONCAT_DETAIL(expr1, expr2)

#define NE_EXPAND(x) x
