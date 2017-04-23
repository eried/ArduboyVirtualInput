const int KEYBOARD = 0, MOUSE = 1;
int loopMode = KEYBOARD;

void mainLoop()
{
  switch (loopMode)
  {
    case KEYBOARD:
      // Smooth scroll
      inix +=  (nx - inix) / KEYBOARD_SCROLL;
      iniy +=  (ny - iniy) / KEYBOARD_SCROLL;

      inix = round(inix * 10) / 10;
      iniy = round(iniy * 10) / 10;

      if (millis() > waitForRelease) // Assume is a new keypress
      {
        if (arduboy.pressed(RIGHT_BUTTON) || arduboy.pressed(LEFT_BUTTON))
        {
          selectedBlock = getNearBlock(selectedBlock, arduboy.pressed(RIGHT_BUTTON));
          waitForRelease = millis() + DEBOUNCE;
        }

        if (arduboy.pressed(UP_BUTTON) || arduboy.pressed(DOWN_BUTTON))
        {
          block b = getBlock(selectedBlock);
          selectedBlock += arduboy.pressed(UP_BUTTON) ? -b.upper : b.lower;
          waitForRelease = millis() + DEBOUNCE;
        }

        if (arduboy.pressed(B_BUTTON) )
        {
          if (mouseBlock == selectedBlock)
            selectedBlock = previousBlock;
          else
          {
            previousBlock = selectedBlock;
            selectedBlock = mouseBlock;
          }
          waitForRelease = millis() + DEBOUNCE;
        }

        if (arduboy.pressed(A_BUTTON) )
        {
          block b = getBlock(selectedBlock);

          switch (b.type)
          {
            case NORMAL:
              Keyboard.write(b.label[0]);
              break;

            case EXTENDED:
              Keyboard.write(b.value);
              break;

            case SPECIAL:
              switch (b.value)
              {
                case 1: // Mouse mouse
                  loopMode = MOUSE;
                  delay(DEBOUNCE);
                  return;
              }
              break;
          }

          waitForRelease = millis() + DEBOUNCE;
        }

      } else
        waitForRelease = arduboy.buttonsState() == 0 ? 0 : waitForRelease;

      drawKeyboard(inix, iniy);
      break;

    case MOUSE:
      arduboy.drawRect(0, 0, 124, 64);
      arduboy.setCursor(47, 2);
      arduboy.print("Mouse");
      arduboy.setCursor(2, 20);
      arduboy.print("Cursor: Move pointer");
      arduboy.setCursor(2, 29);
      arduboy.print("Tap  A: Left click");
      arduboy.setCursor(2, 38);
      arduboy.print("Hold A: Right click");
      arduboy.setCursor(2, 55);
      arduboy.print("Tap  B: Back");

      if (millis() > waitForRelease) // Assume is a new keypress
      {
        if (arduboy.buttonsState() != 0)
        {
          int s = MOUSE_SPEED + (mouseHeld * MOUSE_ACCEL);
          if (arduboy.pressed(RIGHT_BUTTON)) Mouse.move(s, 0);
          if (arduboy.pressed(LEFT_BUTTON)) Mouse.move(-s, 0);
          if (arduboy.pressed(DOWN_BUTTON)) Mouse.move(0, s);
          if (arduboy.pressed(UP_BUTTON)) Mouse.move(0, -s);
          waitForRelease = millis() + MOUSE_DEBOUNCE - mouseHeld;

          if (s < MOUSE_MAXACCEL)
            mouseHeld++;
        }
      }

      if ( arduboy.buttonsState() == 0)
      {
        mouseHeld = 0;
        waitForRelease = 0;
      }

      if (arduboy.pressed(A_BUTTON) )
      {
        long t = millis() + MOUSE_DELAY;

        do {
          if (!arduboy.pressed(A_BUTTON)) break;
        } while (millis() < t);
        t -= millis();

        //if (arduboy.buttonsState() == B00001000)
        Mouse.click(t > 0 ? MOUSE_LEFT : MOUSE_RIGHT);
        /*else
          Mouse.press();*/
        do {} while (arduboy.pressed(A_BUTTON)); // Wait for release
      }
      /*else
        Mouse.release();*/

      if (arduboy.pressed(B_BUTTON) )
      {
        loopMode = KEYBOARD;
        selectedBlock = previousBlock;
        waitForRelease = millis() + DEBOUNCE;
      }

      break;
  }
}

void loop()
{
  if (!(arduboy.nextFrame()))
    return;
  arduboy.clear();
  mainLoop();

  // Mirroring
  //Serial.write(arduboy.getBuffer(), 128 * 64 / 8);
  arduboy.display();
}
