import { setLoggedIn } from '@/features/user/userSlice';
import { useAppDispatch, useAppSelector } from '@/hooks';
import Dialog, { DialogBody, DialogButtons } from '@/ui/components/dialog/Dialog';
import api from '@/utils/api';
import {
  Button,
  FormControl,
  FormErrorMessage,
  FormLabel,
  Input,
  Text,
  useDisclosure,
  useToast,
} from '@chakra-ui/react';
import { AxiosError } from 'axios';
import React from 'react';
import { useForm } from 'react-hook-form';
import { useMutation } from 'react-query';

type LoginRequestData = {
  email: string;
  password: string;
};

const Login = () => {
  const toast = useToast();
  const isLoggedIn = useAppSelector((state) => state.user.isLoggedIn);
  const dispatch = useAppDispatch();

  const { isOpen: isLoginDialogOpen, onOpen: onLoginDialogOpen, onClose: onLoginDialogClose } = useDisclosure();
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
    mutateAsync: mutateLogin,
    isError: isLoginError,
    error: loginError,
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

  const logOut = async () => {
    try {
      await fetch('/users/sign_out', {
        method: 'DELETE',
        headers: {
          'X-CSRF-Token': document.querySelector('meta[name="csrf-token"]')?.getAttribute('content') || '',
        },
      });
      toast({
        title: 'Logged out successfully',
        position: 'top',
      });
    } catch (e) {}
  };

  const handleClose = () => {
    resetForm();
    onLoginDialogClose();
  };

  const onSubmit = async (data: LoginRequestData) => {
    await mutateLogin(data);
    dispatch(setLoggedIn(true));
    handleClose();
  };

  return (
    <>
      {isLoggedIn ? (
        <Button size="sm" onClick={logOut}>
          Log out
        </Button>
      ) : (
        <Button size="sm" onClick={onLoginDialogOpen}>
          Log in
        </Button>
      )}
      <Dialog isOpen={isLoginDialogOpen} onClose={handleClose} title="Log in">
        <DialogBody as="form" onSubmit={handleSubmit(onSubmit)}>
          <FormControl isInvalid={Boolean(errors.email)}>
            <FormLabel>Email</FormLabel>
            <Input
              {...register('email', {
                required: {
                  value: true,
                  message: 'Please enter your email address',
                },
                pattern: {
                  value:
                    /^(([^<>()[\]\\.,;:\s@\"]+(\.[^<>()[\]\\.,;:\s@\"]+)*)|(\".+\"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/,
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
          {isLoginError && (
            <Text color="red.300" fontSize="--chakra - fontSizes - sm">
              {loginError?.response?.status === 401 ? 'Invalid email or password' : 'Failed to log in'}
            </Text>
          )}
          <DialogButtons>
            <Button size="sm" onClick={handleClose}>
              Close
            </Button>
            <Button size="sm" colorScheme="orange" type="submit">
              Log in
            </Button>
          </DialogButtons>
        </DialogBody>
      </Dialog>
    </>
  );
};

export default Login;
