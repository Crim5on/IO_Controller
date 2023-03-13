#pragma once 


/** @return a word with only bit-th bit set. */
#define BIT(bit) (1u << bit)

/** Raise bit-th bit in word. */
#define BIT_SET(word, bit) ((word) |= BIT(bit))

/** Clear bit-th bit in word. */
#define BIT_CLR(word, bit) ((word) &= ~BIT(bit))

/** Toggle the bit-th bit in word. */
#define BIT_TOGGLE(word, bit) ((word) ^= BIT(bit))

/** @return value "1" if bit-th bit of word is set and zero otherwise. */
#define BIT_IS_SET(y, pos) ((0u == ((y) & (BIT(pos)))) ? 0u : 1u)
