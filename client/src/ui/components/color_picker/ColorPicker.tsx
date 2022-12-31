import Settings from '@/services/settings/Settings';
import { Button, Popover, PopoverArrow, PopoverBody, PopoverContent, PopoverTrigger } from '@chakra-ui/react';
import { observer } from 'mobx-react-lite';
import React, { useState } from 'react';
import { ChromePicker } from 'react-color';
import Icon from '../icon/Icon';

type ColorPickerProps = {
  editorStore: Settings;
};

const ColorPicker = observer(({ editorStore }: ColorPickerProps) => {
  const [color, setColor] = useState('#000000');

  const handleChangeComplete = () => {
    editorStore.setColor(color);
  };

  return (
    <Popover placement="right">
      <PopoverTrigger>
        <Button className="iconOnly">
          <Icon name="BiFontColor" />
        </Button>
      </PopoverTrigger>
      <PopoverContent width="250px">
        <PopoverArrow />
        <PopoverBody>
          <ChromePicker
            color={color}
            onChange={(newColor) => setColor(newColor.hex)}
            onChangeComplete={handleChangeComplete}
          />
        </PopoverBody>
      </PopoverContent>
    </Popover>
  );
});

export default ColorPicker;
