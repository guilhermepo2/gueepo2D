#pragma once

#define unreferenced(...) (__VA_ARGS__)
#define unref(...) unreferenced(__VA_ARGS__)

#define BIT(x) (1 << x)
