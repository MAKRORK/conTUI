#pragma once

namespace ctui
{
	class CTKey
	{
	public:
		// --- Control keys ---
		const static int CTK_BACKSPACE = 0x08;
		const static int CTK_TAB = 0x09;
		const static int CTK_ENTER = 0x0D;
		const static int CTK_SHIFT = 0x10;
		const static int CTK_CTRL = 0x11;
		const static int CTK_ALT = 0x12;
		const static int CTK_PAUSE = 0x13;
		const static int CTK_CAPS = 0x14;
		const static int CTK_ESC = 0x1B;
		const static int CTK_SPACE = 0x20;

		// --- Arrows ---
		const static int CTK_LEFT = 0x25;
		const static int CTK_UP = 0x26;
		const static int CTK_RIGHT = 0x27;
		const static int CTK_DOWN = 0x28;

		// --- F1–F12 ---
		const static int CTK_F1 = 0x70;
		const static int CTK_F2 = 0x71;
		const static int CTK_F3 = 0x72;
		const static int CTK_F4 = 0x73;
		const static int CTK_F5 = 0x74;
		const static int CTK_F6 = 0x75;
		const static int CTK_F7 = 0x76;
		const static int CTK_F8 = 0x77;
		const static int CTK_F9 = 0x78;
		const static int CTK_F10 = 0x79;
		const static int CTK_F11 = 0x7A;
		const static int CTK_F12 = 0x7B;

		// --- Numbers 0–9 ---
		const static int CTK_0 = 0x30;
		const static int CTK_1 = 0x31;
		const static int CTK_2 = 0x32;
		const static int CTK_3 = 0x33;
		const static int CTK_4 = 0x34;
		const static int CTK_5 = 0x35;
		const static int CTK_6 = 0x36;
		const static int CTK_7 = 0x37;
		const static int CTK_8 = 0x38;
		const static int CTK_9 = 0x39;

		// --- Letters A–Z ---
		const static int CTK_A = 0x41;
		const static int CTK_B = 0x42;
		const static int CTK_C = 0x43;
		const static int CTK_D = 0x44;
		const static int CTK_E = 0x45;
		const static int CTK_F = 0x46;
		const static int CTK_G = 0x47;
		const static int CTK_H = 0x48;
		const static int CTK_I = 0x49;
		const static int CTK_J = 0x4A;
		const static int CTK_K = 0x4B;
		const static int CTK_L = 0x4C;
		const static int CTK_M = 0x4D;
		const static int CTK_N = 0x4E;
		const static int CTK_O = 0x4F;
		const static int CTK_P = 0x50;
		const static int CTK_Q = 0x51;
		const static int CTK_R = 0x52;
		const static int CTK_S = 0x53;
		const static int CTK_T = 0x54;
		const static int CTK_U = 0x55;
		const static int CTK_V = 0x56;
		const static int CTK_W = 0x57;
		const static int CTK_X = 0x58;
		const static int CTK_Y = 0x59;
		const static int CTK_Z = 0x5A;

		// --- Numpad keys ---
		const static int CTK_NUM0 = 0x60;
		const static int CTK_NUM1 = 0x61;
		const static int CTK_NUM2 = 0x62;
		const static int CTK_NUM3 = 0x63;
		const static int CTK_NUM4 = 0x64;
		const static int CTK_NUM5 = 0x65;
		const static int CTK_NUM6 = 0x66;
		const static int CTK_NUM7 = 0x67;
		const static int CTK_NUM8 = 0x68;
		const static int CTK_NUM9 = 0x69;

		const static int CTK_NUM_MUL = 0x6A;
		const static int CTK_NUM_ADD = 0x6B;
		const static int CTK_NUM_SEP = 0x6C;
		const static int CTK_NUM_SUB = 0x6D;
		const static int CTK_NUM_DEC = 0x6E;
		const static int CTK_NUM_DIV = 0x6F;

		// --- Other ---
		const static int CTK_INSERT = 0x2D;
		const static int CTK_DELETE = 0x2E;
		const static int CTK_HOME = 0x24;
		const static int CTK_END = 0x23;
		const static int CTK_PAGEUP = 0x21;
		const static int CTK_PAGEDOWN = 0x22;
		const static int CTK_PRINTSCR = 0x2C;
		const static int CTK_SCROLL = 0x91;
		const static int CTK_NUMLOCK = 0x90;
	};

}
