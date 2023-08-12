import { Box } from '@chakra-ui/react';
import React from 'react';
import { useEffect } from 'react';

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
