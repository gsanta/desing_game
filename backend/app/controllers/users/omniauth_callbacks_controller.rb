class Users::OmniauthCallbacksController < Devise::OmniauthCallbacksController
   def google_oauth2
     user = User.from_google(from_google_params)

     if user.present?
       sign_out_all_scopes
       flash[:notice] = t 'devise.omniauth_callbacks.success', kind: 'Google'
       sign_in_and_redirect user, event: :authentication
     else
       flash[:alert] = t 'devise.omniauth_callbacks.failure', kind: 'Google', reason: "#{auth.info.email} is not authorized."
       # redirect_to new_user_session_path
     end
     # render json: {
     #   name: "abcd"
     # }
   end

   def facebook
     puts "facebook callback called"
   end

   def self.from_omniauth(access_token)
     puts "from_omniauth entered"

     data = access_token.info
     user = User.where(email: data['email']).first

     # Uncomment the section below if you want users to be created if they don't exist
     # unless user
     #     user = User.create(name: data['name'],
     #        email: data['email'],
     #        password: Devise.friendly_token[0,20]
     #     )
     # end
     user
   end

    def from_google_params
      @from_google_params ||= {
        uid: auth.uid,
        email: auth.info.email
      }
    end

    def auth
      @auth ||= request.env['omniauth.auth']
    end
end
