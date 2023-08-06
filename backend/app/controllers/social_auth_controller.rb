# Api Controller to handle our call backs
require 'json'
class SocialAuthController < ApplicationController
  def authenticate_social_auth_user
    validate_access_token
    @user = User.signin_or_create_from_provider(params) # this method add a user who is new or logins an old one
    if @user.persisted?
      sign_in(@user)
      render json: {
        status: 'SUCCESS',
        message: "user was successfully logged in through #{params[:provider]}"
      },
             status: :created
    else
      render json: {
        status: 'FAILURE',
        message: "There was a problem signing you in through #{params[:provider]}",
        data: @user.errors
      },
             status: :unprocessable_entity
    end
  end

  def validate_access_token
    access_token = request.headers['Authorization']&.gsub(/bearer /i, '')
    key_source = Google::Auth::IDTokens::JwkHttpKeySource.new(Google::Auth::IDTokens::OAUTH2_V3_CERTS_URL)
    verifier = Google::Auth::IDTokens::Verifier.new(key_source: key_source)
    verifier.verify(access_token)
  rescue Google::Auth::IDTokens::VerificationError => e
    puts e.message
  end
end
