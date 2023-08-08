# Api Controller to handle our call backs
class Users::GoogleAuthController < ApplicationController
  def authenticate
    access_token = request.headers['Authorization']&.gsub(/bearer /i, '')
    email = verifier.verify access_token
    user = User.sign_in_or_create_for_google(email)

    render json: {

    }



    # render json: TaskPresenter.new(task).to_h, status: :created
    # if @user.persisted?
    #   sign_in(@user)
    #   render json: {
    #     status: 'SUCCESS',
    #     message: "user was successfully logged in through #{params[:provider]}"
    #   },
    #          status: :created
    # else
    #   render json: {
    #     status: 'FAILURE',
    #     message: "There was a problem signing you in through #{params[:provider]}",
    #     data: @user.errors
    #   },
    #          status: :unprocessable_entity
    # end
  end

  def verifier
    @verifier ||= GoogleAccessTokenVerifier.new
  end
end
