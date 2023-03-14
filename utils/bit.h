#pragma once 


/** @return a byte with only bit-th bit set. */
#define BIT(bit) (1u << bit)

/** Raise bit-th bit in byte. */
#define BIT_SET(byte, bit) ((byte) |= BIT(bit))

/** Clear bit-th bit in byte. */
#define BIT_CLR(byte, bit) ((byte) &= ~BIT(bit))

/** Toggle the bit-th bit in byte. */
#define BIT_TOGGLE(byte, bit) ((byte) ^= BIT(bit))

/** Override bit-th bit in byte with val (true / false). */
#define BIT_OVERRIDE_WITH_VAL(byte, bit, val) ((val) ? BIT_SET(byte, bit) : BIT_CLR(byte, bit))

/** @return 1 if bit-th bit of byte is set and 0 otherwise. */
#define BIT_IS_SET(byte, bit) ((0u == ((y) & (BIT(pos)))) ? 0u : 1u)

