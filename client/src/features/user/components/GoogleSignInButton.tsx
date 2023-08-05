import api from '@/utils/api';
import React from 'react';
import { useEffect } from 'react';

const GoogleSignInButton = () => {
  const signInCallback = (result: any) => {
    if (result.credential) {
      const params = { token: result.credential };
      api
        .post('/users/auth/google_oauth2/callback', params)
        .then((res) => {
          const { authToken, ...userInfo } = res.data.data;
          // set token in local storage/cookies based on your authentication method
          // redirect to the authenticated page
        })
        .catch((err) => console.log(err));
    }
  };

  useEffect(() => {
    google.accounts.id.initialize({
      client_id: process.env.GOOGLE_OAUTH_CLIENT_ID,
      callback: signInCallback,
      cancel_on_tap_outside: false,
    });

    google.accounts.id.renderButton(document.getElementById('signInDiv'), {
      theme: 'outline',
      size: 'medium',
    });
  }, []);

  return <div id="signInDiv" />;
};

export default GoogleSignInButton;
