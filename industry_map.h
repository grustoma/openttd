/* $Id$ */

/** @file industry_map.h Accessors for industries */

#ifndef INDUSTRY_MAP_H
#define INDUSTRY_MAP_H

#include "industry.h"
#include "macros.h"
#include "tile.h"

typedef uint IndustryGfx;

static inline uint GetIndustryIndex(TileIndex t)
{
	assert(IsTileType(t, MP_INDUSTRY));
	return _m[t].m2;
}

static inline Industry* GetIndustryByTile(TileIndex t)
{
	return GetIndustry(GetIndustryIndex(t));
}

static inline bool IsIndustryCompleted(TileIndex t)
{
	assert(IsTileType(t, MP_INDUSTRY));
	return HASBIT(_m[t].m1, 7);
}

IndustryType GetIndustryType(TileIndex tile);

/**
 * Set if the industry that owns the tile as under construction or not
 * @param tile the tile to query
 * @param isCompleted whether it is completed or not
 * @pre IsTileType(tile, MP_INDUSTRY)
 */
static inline void SetIndustryCompleted(TileIndex tile, bool isCompleted)
{
	assert(IsTileType(tile, MP_INDUSTRY));
	SB(_m[tile].m1, 7, 1, isCompleted ? 1 :0);
}

/**
 * Returns the industry construction stage of the specified tile
 * @param tile the tile to query
 * @pre IsTileType(tile, MP_INDUSTRY)
 * @return the construction stage
 */
static inline byte GetIndustryConstructionStage(TileIndex tile)
{
	assert(IsTileType(tile, MP_INDUSTRY));
	return GB(_m[tile].m1, 0, 2);
}

/**
 * Sets the industry construction stage of the specified tile
 * @param tile the tile to query
 * @param value the new construction stage
 * @pre IsTileType(tile, MP_INDUSTRY)
 */
static inline void SetIndustryConstructionStage(TileIndex tile, byte value)
{
	assert(IsTileType(tile, MP_INDUSTRY));
	SB(_m[tile].m1, 0, 2, value);
}

static inline IndustryGfx GetIndustryGfx(TileIndex t)
{
	assert(IsTileType(t, MP_INDUSTRY));
	return _m[t].m5;
}

static inline void SetIndustryGfx(TileIndex t, IndustryGfx gfx)
{
	assert(IsTileType(t, MP_INDUSTRY));
	_m[t].m5 = gfx;
}

static inline void MakeIndustry(TileIndex t, uint index, uint gfx)
{
	SetTileType(t, MP_INDUSTRY);
	_m[t].m1 = 0;
	_m[t].m2 = index;
	_m[t].m3 = 0;
	_m[t].m4 = 0;
	_m[t].m5 = gfx;
}

/**
 * Returns this indutry tile's construction counter value
 * @param tile the tile to query
 * @pre IsTileType(tile, MP_INDUSTRY)
 * @return the construction counter
 */
static inline byte GetIndustryConstructionCounter(TileIndex tile)
{
	assert(IsTileType(tile, MP_INDUSTRY));
	return GB(_m[tile].m1, 2, 2);
}

/**
 * Sets this indutry tile's construction counter value
 * @param tile the tile to query
 * @param value the new value for the construction counter
 * @pre IsTileType(tile, MP_INDUSTRY)
 */
static inline void SetIndustryConstructionCounter(TileIndex tile, byte value)
{
	assert(IsTileType(tile, MP_INDUSTRY));
	SB(_m[tile].m1, 2, 2, value);
}

/**
 * Reset the construction stage counter of the industry,
 * as well as the completion bit.
 * In fact, it is the same as restarting construction frmo ground up
 * @param tile the tile to query
 * @param generating_world whether generating a world or not
 * @pre IsTileType(tile, MP_INDUSTRY)
 */
static inline void ResetIndustryConstructionStage(TileIndex tile)
{
	assert(IsTileType(tile, MP_INDUSTRY));
	_m[tile].m1 = 0;
}

typedef struct IndustryTypeSolver {
	IndustryGfx MinGfx;
	IndustryGfx MaxGfx;
 } IndustryTypeSolver;

static const IndustryTypeSolver industry_gfx_Solver [IT_END] = {
	{  0,   6}, //IT_COAL_MINE
	{  7,  10}, //IT_POWER_STATION,
	{ 11,  15}, //IT_SAWMILL,
	{ 16,  17}, //IT_FOREST,
	{ 18,  23}, //IT_OIL_REFINERY,
	{ 24,  28}, //IT_OIL_RIG,
	{ 29,  31}, //IT_OIL_WELL,
	{ 32,  38}, //IT_FARM,
	{ 39,  42}, //IT_FACTORY,
	{ 43,  46}, //IT_PRINTING_WORKS,
	{ 47,  51}, //IT_COPPER_MINE,
	{ 52,  57}, //IT_STEEL_MILL,
	{ 58,  59}, //IT_BANK_TEMP,
	{ 60,  63}, //IT_FOOD_PROCESS,
	{ 64,  71}, //IT_PAPER_MILL,
	{ 72,  88}, //IT_GOLD_MINE,
	{ 89,  90}, //IT_BANK_TROPIC_ARCTIC,
	{ 91,  99}, //IT_DIAMOND_MINE,
	{100, 115}, //IT_IRON_MINE,
	{116, 116}, //IT_FRUIT_PLANTATION,
	{117, 117}, //IT_RUBBER_PLANTATION,
	{118, 119}, //IT_WATER_SUPPLY,
	{120, 120}, //IT_WATER_TOWER,
	{121, 124}, //IT_FACTORY_2,
	{125, 128}, //IT_LUMBER_MILL,
	{129, 130}, //IT_COTTON_CANDY,
	{131, 134}, //IT_CANDY_FACTORY or sweet factory
	{135, 136}, //IT_BATTERY_FARM,
	{137, 137}, //IT_COLA_WELLS,
	{138, 141}, //IT_TOY_SHOP,
	{142, 147}, //IT_TOY_FACTORY,
	{148, 155}, //IT_PLASTIC_FOUNTAINS,
	{156, 159}, //IT_FIZZY_DRINK_FACTORY,
	{160, 163}, //IT_BUBBLE_GENERATOR,
	{164, 166}, //IT_TOFFEE_QUARRY,
	{167, 174}  //IT_SUGAR_MINE,
};

#endif /* INDUSTRY_MAP_H */
