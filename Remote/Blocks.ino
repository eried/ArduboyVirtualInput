// Is the block a key or a special markup?
bool isKey(byte b)
{
  switch (b)
  {
    case NORMAL:
    case EXTENDED:
    case SPECIAL:
      return true;
  }
  return false;
}

int keyWidth(char c[])
{
  return 9 + ((strlen(c) - 1) * 6);
}

// Complete keyboard and touchpad layout
const block layout[] PROGMEM  = {
  /* Function keys */


  /* Standard keyboard */

  {"", 2, SPACER, 0, 0}, {"1", 0, NORMAL, 0, 13},  {"2", 0, NORMAL, 0, 12},  {"3", 0, NORMAL, 0, 12},  {"4", 0, NORMAL, 0, 12},  {"5", 0, NORMAL, 0, 12},  {"6", 0, NORMAL, 0, 12},
  {"7", 0, NORMAL, 0, 12},  {"8", 0, NORMAL, 0, 12},  {"9", 0, NORMAL, 0, 12},  {"0", 0, NORMAL, 0, 12},  {"Del", KEY_BACKSPACE, EXTENDED, 0, 12},
  {"", 0, SPLITTER, 0, 0},
  {"", 2, SPACER, 0, 0}, {"Tab", KEY_TAB, EXTENDED, 13, 13},  {"Q", 0, NORMAL, 12, 14},  {"W", 0, NORMAL, 12, 14},  {"E", 0, NORMAL, 12, 14},  {"R", 0, NORMAL, 12, 14},
  {"T", 0, NORMAL, 12, 14}, {"Y", 0, NORMAL, 12, 14},  {"U", 0, NORMAL, 12, 14},  {"I", 0, NORMAL, 12, 14},  {"O", 0, NORMAL, 12, 13}, {"P", 0, NORMAL, 13, 12},
  {"", 0, SPLITTER, 0, 0},
  {"", 1, SPACER, 0, 0}, {"A", 0, NORMAL, 13, 12},  {"S", 0, NORMAL, 14, 11},  {"D", 0, NORMAL, 14, 10},  {"F", 0, NORMAL, 14, 10},  {"G", 0, NORMAL, 14, 10},
  {"H", 0, NORMAL, 14, 10},  {"J", 0, NORMAL, 14, 10},  {"K", 0, NORMAL, 14, 10},  {"L", 0, NORMAL, 14, 10},  {"Enter", KEY_RETURN, EXTENDED, 14, 10},
  {"", 0, SPLITTER, 0, 0},
  {"", 1, SPACER, 0, 0}, {"Shift", 0, EXTENDED, 12, 12},  {"Z", 0, NORMAL, 10, 12},  {"X", 0, NORMAL, 10, 11},  {"C", 0, NORMAL, 10, 11},  {"V", 0, NORMAL, 10, 10},
  {"B", 0, NORMAL, 10, 9}, {"N", 0, NORMAL, 10, 8},  {"M", 0, NORMAL, 10, 8},  {",", 0, NORMAL, 11, 7},  {".", 0, NORMAL, 12, 6}, /* {"-", 0, NORMAL,11,11},*/
  {"", 0, SPLITTER, 0, 0},
  {"", 1, SPACER, 0, 0}, {"Ctrl", KEY_LEFT_CTRL, EXTENDED, 12, 7},  {"Alt", KEY_LEFT_ALT, EXTENDED, 12, 9},  {"        ", ' ', EXTENDED, 11, 11},
  {"Win", KEY_LEFT_GUI, EXTENDED, 7, 10},  {"", 0, PLACEHOLDER, 0, 0},
  {"", 0, SPLITTER, 0, 0},

  /* Bottom */
  {"", 12, SPACER, 0, 0}, {{24,}, KEY_UP_ARROW, EXTENDED, 7, 0}, {{25,}, KEY_DOWN_ARROW, EXTENDED, 8, 0}, {"", 4, SPACER, 0, 0},
  {{27,}, KEY_LEFT_ARROW, EXTENDED, 9, 0}, {{26,}, KEY_RIGHT_ARROW, EXTENDED, 10, 0}, {"", 4, SPACER, 0, 0},
  {"Mouse...", 1, SPECIAL, 11, 0},

  /* End */
  {"", 0, TERMINATOR, 0, 0},

};

// Gets a block from the PROGMEM
block getBlock(int n)
{
  block b;
  memcpy_P (&b, &layout [n], sizeof b);
  return b;
}

// Gets the next valid block
int getNearBlock(int n, bool forward = true)
{
  do
  {
    n += (forward ? 1 : -1);

    if (n < 0)
      return getNearBlock(n);
    else
    {
      block b = getBlock(n);

      if (isKey(b.type))
        return n;
      else if (b.type == TERMINATOR)
        return getNearBlock(n, false);
    }
  } while (true);
}
