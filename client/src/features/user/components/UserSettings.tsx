import { setLoggedIn } from '@/features/user/userSlice';
import { useAppDispatch, useAppSelector } from '@/hooks';
import { Button, ButtonGroup, useDisclosure, useToast } from '@chakra-ui/react';
import React from 'react';
import SignUpDialog from './SignUpDialog';
import SignInDialog from './SignInDialog';

const UserSettings = () => {
  const toast = useToast();
  const isLoggedIn = useAppSelector((state) => state.user.isLoggedIn);
  const dispatch = useAppDispatch();

  const { isOpen: isSignInDialogOpen, onOpen: onSignInDialogOpen, onClose: onSignInDialogClose } = useDisclosure();
  const { isOpen: isSignUpDialogOpen, onOpen: onSignUpDialogOpen, onClose: onSignUpDialogClose } = useDisclosure();

  const logOut = async () => {
    try {
      await fetch('/users/sign_out', {
        method: 'DELETE',
        headers: {
          'X-CSRF-Token': document.querySelector('meta[name="csrf-token"]')?.getAttribute('content') || '',
        },
      });
      dispatch(setLoggedIn(false));
      toast({
        title: 'Logged out successfully',
        position: 'top',
      });
    } catch (e) {}
  };

  return (
    <>
      {isLoggedIn ? (
        <Button size="sm" onClick={logOut}>
          Log out
        </Button>
      ) : (
        <ButtonGroup>
          <Button size="sm" onClick={onSignInDialogOpen}>
            Log in
          </Button>
          <Button size="sm" onClick={onSignUpDialogOpen}>
            Sign up
          </Button>
        </ButtonGroup>
      )}
      <SignInDialog isOpen={isSignInDialogOpen} onClose={onSignInDialogClose} />
      <SignUpDialog isOpen={isSignUpDialogOpen} onClose={onSignUpDialogClose} />
    </>
  );
};

export default UserSettings;
