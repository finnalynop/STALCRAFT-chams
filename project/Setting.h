#pragma once

bool wallhackEnabled = false;
bool wallhackEnabledv2 = false;

bool chamsEnabled = false;
bool deleteEffects = false;


BYTE wallhackInstruction[] = { 0x48, 0xC1, 0xE1, 0x04 }; // shl rcx,04
BYTE newWallHackInstruction[] = { 0x41, 0xC1, 0xE1, 0x04 };

BYTE deleteEffectsInstruction[] = { 0x41, 0xC1, 0xE1, 0x04 };

BYTE chamsInstruction[] = { 0x48, 0xC1, 0xE1, 0x04 };
BYTE newChamsInstruction[] = { 0x48, 0xC1, 0xE1, 0x05 };

BYTE newWallhackInstructionv2[] = { 0x48, 0xC1, 0xE9, 0x04 };