Rails.application.routes.draw do
  root "editor#index"
  get "/editor", to: "editor#index"

  resources :drawings, only: %i[index show create update destroy]

  devise_for :users, controllers: {
    sessions: 'users/sessions',
    registrations: 'users/registrations'
  }

  post '/social_auth/callback', to: 'social_auth#authenticate_social_auth_user' # this is the line where we add our routes

  # For details on the DSL available within this file, see https://guides.rubyonrails.org/routing.html
end
