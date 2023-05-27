import SettingsPanel from '@/panels/settings/SettingsPanel';
import { Box } from '@chakra-ui/react';
import React from 'react';
import UserSettings from './UserSettings';

const Header = () => {
  return (
    <Box
      borderBottom="1px solid"
      borderColor="gray.600"
      display="flex"
      justifyContent="space-between"
      height="40px"
      paddingInline="1"
      paddingBlock="1"
    >
      <SettingsPanel />
      <UserSettings />
    </Box>
  );
};

export default Header;
