import FrameButton from '@/ui/components/button/FrameButton';
import { Box, Divider } from '@chakra-ui/react';
import Icon from '@/ui/components/icon/Icon';
import React from 'react';
import { Tooltip, Button } from '@chakra-ui/react';

const Frames = () => {
  const handleFrameSelect = (index: number) => {
    console.log('frame selected: ' + index);
  };

  const activeIndex = 10;

  return (
    <Box>
      <Box display="flex" gap="2" justifyContent="end">
        <Tooltip label="delete frame">
          <Button className="iconOnly" size="sm">
            <Icon name="BiTrashAlt" />
          </Button>
        </Tooltip>
        <Tooltip label="new frame">
          <Button className="iconOnly" size="sm">
            <Icon name="BiPlus" />
          </Button>
        </Tooltip>
      </Box>
      <Divider marginBlock="2" />
      {Array.from({ length: 150 }).map((_, index) => (
        <FrameButton
          index={index}
          isActive={index === activeIndex}
          onFrameSelect={handleFrameSelect}
          marginBlockEnd="0.5"
          marginInlineEnd="0.5"
        />
      ))}
    </Box>
  );
};

export default Frames;
