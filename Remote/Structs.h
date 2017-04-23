// Defines a block
enum blocktype
{
  NORMAL, EXTENDED, SPECIAL, SPACER, SPLITTER, TERMINATOR, PLACEHOLDER
};

// Defines the screen layout
typedef struct 
{
  char label[10];
  byte value;
  blocktype type;
  byte upper; // Offset to jump to upper line
  byte lower; // Offset to jump to lower line
} block;

