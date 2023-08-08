import api from '@/utils/api';
import React from 'react';
import { useEffect } from 'react';

const GoogleLogin = () => {
  const handleCallbackResponse = (response: { credential?: string }) => {
    return api
      .post('/users/sign_in/google', undefined, {
        headers: {
          Authorization: `Bearer ${response.credential}`,
          'Content-Type': 'application/json',
        },
      })
      .then((response) => {
        console.log(response, 'I AM  RESPONSE FROM THE BACKEND WITH THE USER LOGIN TOKEN AND HEADERS');
        // set cookies or something
      })
      .catch((err) => err);
  };

  useEffect(() => {
    google.accounts.id.initialize({
      client_id: process.env.GOOGLE_OAUTH_CLIENT_ID,
      callback: handleCallbackResponse,
      cancel_on_tap_outside: false,
    });

    google.accounts.id.renderButton(document.getElementById('signInDiv'), {
      theme: 'outline',
      size: 'medium',
    });
  }, []);

  return <div id="signInDiv" />;
};

export default GoogleLogin;
