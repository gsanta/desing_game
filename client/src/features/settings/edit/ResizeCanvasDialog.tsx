import React from 'react';
import Dialog, { DialogProps, DialogBody, DialogFooter } from '@/components/dialog/Dialog';
import { Button, FormControl, FormLabel, Input } from '@chakra-ui/react';

const ResizeCanvasDialog = ({ isOpen, onClose }: Omit<DialogProps, 'title' | 'children'>) => {
  const handleSubmit = () => {
    onClose();
  };

  return (
    <Dialog isOpen={isOpen} onClose={onClose} title="Resize canvas">
      <DialogBody>
        <FormControl display="flex" flexDirection="row" marginTop="4">
          <FormLabel size="xs">Width:</FormLabel>
          <Input size="xs" width="12" />
        </FormControl>
        <FormControl display="flex" flexDirection="row" marginTop="4">
          <FormLabel size="xs">Height:</FormLabel>
          <Input size="xs" width="12" />
        </FormControl>
      </DialogBody>
      <DialogFooter>
        <Button size="sm" onClick={onClose}>
          Close
        </Button>
        <Button size="sm" colorScheme="orange" onClick={handleSubmit}>
          Resize
        </Button>
      </DialogFooter>
    </Dialog>
  );
};

export default ResizeCanvasDialog;
