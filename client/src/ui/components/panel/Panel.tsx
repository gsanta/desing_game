import { Box, Divider, Text } from '@chakra-ui/react';
import React from 'react';
import { ReactNode } from 'react';

type PanelProps = {
  children: ReactNode;
  header: ReactNode;
};

const Panel = ({ children, header }: PanelProps) => (
  <section>
    {header}
    <div>{children}</div>
  </section>
);

type PanelHeaderProps = {
  children: ReactNode;
  title: string;
};

Panel.Header = ({ children, title }: PanelHeaderProps) => (
  <Box paddingInline="2">
    <Box alignItems="center" display="flex" justifyContent="space-between">
      <Text color="gray.300" fontWeight="bold" paddingInlineStart="2" textTransform="uppercase">
        {title}
      </Text>
      {children && children}
    </Box>
    <Divider />
  </Box>
);

export default Panel;