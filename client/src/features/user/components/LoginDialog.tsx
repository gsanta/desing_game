import { setUser } from '@/features/user/userSlice';
import { useAppDispatch } from '@/hooks';
import Dialog, { DialogBody, DialogButtons, DialogFooter } from '@/components/dialog/Dialog';
import api from '@/utils/api';
import { FormControl, FormLabel, Input, FormErrorMessage, Button, Text, Box } from '@chakra-ui/react';
import { AxiosError } from 'axios';
import React from 'react';
import { useForm } from 'react-hook-form';
import { useMutation } from 'react-query';
import { emailRegex } from '../utils/userUtils';
import GoogleLogin from './GoogleLogin';

type LoginDialogProps = {
  isOpen: boolean;
  onClose(): void;
};

type LoginRequestData = {
  email: string;
  password: string;
};

const LoginDialog = ({ isOpen, onClose }: LoginDialogProps) => {
  const dispatch = useAppDispatch();

  const {
    register,
    handleSubmit,
    formState: { errors },
    reset: resetForm,
  } = useForm({
    defaultValues: {
      email: '',
      password: '',
    },
    mode: 'onBlur',
  });

  const {
    mutateAsync: mutateSignIn,
    isError: isSignInError,
    error: signInError,
  } = useMutation<unknown, AxiosError<unknown>, LoginRequestData>(
    async (data) => {
      const resp = await api.post('/users/sign_in', {
        user: data,
      });
      return resp;
    },
    {
      onError: (error) => {
        console.log(error);
      },
    },
  );

  const handleClose = () => {
    resetForm();
    onClose();
  };

  const onSubmit = async (data: LoginRequestData) => {
    await mutateSignIn(data);
    dispatch(setUser({ isLoggedIn: true, email: data.email }));
    handleClose();
  };

  return (
    <Dialog isOpen={isOpen} onClose={handleClose} title="Log in">
      <form onSubmit={handleSubmit(onSubmit)}>
        <DialogBody>
          <FormControl isInvalid={Boolean(errors.email)}>
            <FormLabel>Email</FormLabel>
            <Input
              {...register('email', {
                required: {
                  value: true,
                  message: 'Please enter your email address',
                },
                pattern: {
                  value: emailRegex,
                  message: 'Invalid email address',
                },
              })}
            />
            <FormErrorMessage>{errors.email?.message}</FormErrorMessage>
          </FormControl>
          <FormControl>
            <FormLabel>Password</FormLabel>
            <Input type="password" {...register('password')} />
          </FormControl>
          <Box display="flex" marginTop="4" justifyContent="space-around">
            <GoogleLogin />
          </Box>
          {isSignInError && (
            <Text color="red.300" fontSize="--chakra - fontSizes - sm">
              {signInError?.response?.status === 401 ? 'Invalid email or password' : 'Failed to log in'}
            </Text>
          )}
        </DialogBody>
        <DialogFooter>
          <DialogButtons>
            <Button size="sm" onClick={handleClose}>
              Close
            </Button>
            <Button size="sm" colorScheme="orange" type="submit">
              Log in
            </Button>
          </DialogButtons>
        </DialogFooter>
      </form>
    </Dialog>
  );
};

export default LoginDialog;
