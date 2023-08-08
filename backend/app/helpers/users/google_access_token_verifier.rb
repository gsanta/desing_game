

module Users
  class GoogleAccessTokenVerifier

    def verify(access_token)
      key_source = Google::Auth::IDTokens::JwkHttpKeySource.new(Google::Auth::IDTokens::OAUTH2_V3_CERTS_URL)
      verifier = Google::Auth::IDTokens::Verifier.new(key_source: key_source)
      token_info = verifier.verify(access_token)
      token_info["email"]
    end
  end
end
