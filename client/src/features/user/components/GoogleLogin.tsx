import { ServerError } from '@/components/ErrorMessage';
import api from '@/utils/api';
import { Box } from '@chakra-ui/react';
import { AxiosError } from 'axios';
import React from 'react';
import { useEffect } from 'react';
import { useMutation } from 'react-query';

export const useGoogleLogin = () => {
  const { mutate, error, isError, isLoading, reset } = useMutation<unknown, AxiosError<ServerError>, string>(
    (credential) =>
      api.post('/users/sign_in/google', undefined, {
        headers: {
          Authorization: `Bearer ${credential}1`,
          'Content-Type': 'application/json',
        },
      }),
  );

  return {
    login: (credential: string) => mutate(credential),
    error,
    isError,
    isLoading,
    reset,
  };
};

type GoogleLoginProps = {
  onLogin(credential: string): void;
};

const GoogleLogin = ({ onLogin }: GoogleLoginProps) => {
  const handleLogin = async (response: { credential?: string }) => {
    response.credential && onLogin(response.credential);
  };

  useEffect(() => {
    if (google) {
      google.accounts.id.initialize({
        client_id: process.env.GOOGLE_OAUTH_CLIENT_ID,
        callback: handleLogin,
        cancel_on_tap_outside: false,
      });

      google.accounts.id.renderButton(document.getElementById('signInDiv'), {
        theme: 'outline',
        size: 'medium',
      });
    }
  }, [google]);

  return <Box id="signInDiv" marginBottom="20px" />;
};

export default GoogleLogin;
