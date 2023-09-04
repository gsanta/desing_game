import { useAppSelector } from '@/hooks';
import { Box, Button, FormControl, FormLabel, Input } from '@chakra-ui/react';
import React, { useState } from 'react';

const SelectToolOptions = () => {
  const editor = useAppSelector((state) => state.editor.editor);
  const [horizontalShear, setHorizontalShear] = useState('');

  const handleApplyShear = () => {
    editor.shearHorizontal((Number(horizontalShear) * Math.PI) / 180);
  };

  return (
    <Box padding="4">
      <FormControl width="40">
        <FormLabel htmlFor="eraser-size-slider" fontSize="sm">
          Shear horizontal (%)
        </FormLabel>
        <Box display="flex" gap="2">
          <Input
            type="number"
            min="0"
            max="100"
            size="sm"
            value={horizontalShear}
            onChange={(e) => setHorizontalShear(e.target.value)}
          />
          <Button size="sm" onClick={handleApplyShear}>
            Apply
          </Button>
        </Box>
      </FormControl>
    </Box>
  );
};

export default SelectToolOptions;
