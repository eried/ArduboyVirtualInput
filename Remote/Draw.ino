void drawKey(char c[], int x, int y, int w, int h)
{

  arduboy.setCursor(x + 2, y + 2);
  arduboy.print(c);
  arduboy.drawRect(x, y, w, h);
}

void drawKeyboard(int x, int y)
{
  byte i = 0;
  int xpos = x, ypos = y;
  int w = 0;

  do
  {
    block b = getBlock(i);

    switch (b.type)
    {

      case EXTENDED:
      case SPECIAL:
      case NORMAL:
        w = keyWidth(b.label);
        drawKey(b.label, xpos, ypos, w, 11);

        if (selectedBlock == i)
        {
          // Change focus position to scroll the keyboard to selected block
          ny = 24 + (iniy - (ypos));

          if (waitForRelease > 0 || millis() % 1000 > 500) // 50% of the time blinking is off
            arduboy.drawRect(xpos - 1, ypos - 1, w + 2, 13);
        }

        xpos += w + 1;
        break;

      case SPLITTER:
        xpos = x;
        ypos += 12;
        break;

      case SPACER:
        xpos += (int)(b.value);
        break;

      case TERMINATOR:
        goto exit;
    }
    i++;
  } while (true);
exit:;
}

