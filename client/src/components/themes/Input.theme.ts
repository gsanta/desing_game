import { inputAnatomy as parts } from '@chakra-ui/anatomy';
import { createMultiStyleConfigHelpers } from '@chakra-ui/styled-system';
const { definePartsStyle, defineMultiStyleConfig } = createMultiStyleConfigHelpers(parts.keys);
import { getColor } from '@chakra-ui/theme-tools';

const OutlineVariant = definePartsStyle((props) => {
  const { theme } = props;

  return {
    field: {
      border: '1px solid',
      borderColor: 'inherit',
      bg: 'brand.background',
      _focusVisible: {
        zIndex: 1,
        borderColor: 'orange.400',
        boxShadow: `0 0 0 1px var(--chakra-colors-orange-600)`,
      },
    },
  };
});

const variants = {
  outline: OutlineVariant,
};

export const inputTheme = defineMultiStyleConfig({
  variants,
});
