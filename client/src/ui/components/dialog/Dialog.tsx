import {
  Modal,
  ModalOverlay,
  ModalContent,
  ModalCloseButton,
  ModalHeader,
  usePrefersReducedMotion,
  Text,
  ModalBody,
  ModalBodyProps,
  HStack,
  ModalFooter,
  ModalFooterProps,
  ButtonGroup,
} from '@chakra-ui/react';
import React, { ReactNode } from 'react';
import { BiX } from 'react-icons/bi';

export type DialogProps = {
  children: ReactNode;
  isOpen: boolean;
  onClose(): void;
  title: string;
};

export type DialogBodyProps = ModalBodyProps;

export const DialogBody = (props: DialogBodyProps) => {
  return <ModalBody paddingInline="2" paddingBlockEnd="2" {...props} />;
};

export type DialogFooterProps = ModalFooterProps;

export const DialogFooter = ({ children, ...rest }: DialogFooterProps) => {
  return (
    <ModalFooter paddingInline="2" {...rest}>
      <HStack justifyContent="end">{children}</HStack>
    </ModalFooter>
  );
};

export const DialogButtons = ({ children, ...rest }: DialogFooterProps) => {
  return (
    <ModalFooter paddingInline="2" {...rest}>
      <HStack justifyContent="end">
        <ButtonGroup>{children}</ButtonGroup>
      </HStack>
    </ModalFooter>
  );
};

const Dialog = ({ children, isOpen, onClose, title }: DialogProps) => {
  const prefersReducedMotion = usePrefersReducedMotion();

  return (
    <Modal
      closeOnEsc={true}
      closeOnOverlayClick={false}
      isOpen={isOpen}
      motionPreset={prefersReducedMotion ? 'none' : 'scale'}
      onClose={onClose}
      trapFocus={true}
    >
      <ModalOverlay />
      <ModalContent bgColor="chakra-body-bg">
        <ModalHeader>
          <Text as="h1" color="gray.300" size="3" textTransform="uppercase">
            {title}
          </Text>
        </ModalHeader>
        <ModalCloseButton>
          <BiX size={30} />
        </ModalCloseButton>
        {children}
      </ModalContent>
    </Modal>
  );
};

export default Dialog;
