# frozen_string_literal: true

require "rails_helper"

RSpec.describe Users::GoogleAuthController do

  describe "#authenticate" do
    subject(:authenticate) { post :authenticate }

    let(:token) { "access_token" }
    let(:email) { "test_user@test.com" }
    let(:verifier) { instance_double Users::GoogleAccessTokenVerifier }
    let(:headers) { {Authorization: "Bearer #{token}" }}

    before do
      allow(verifier).to receive(:verify).with(token).and_return email
      allow(controller).to receive(:verifier).and_return(verifier)

      request.env['Authorization'] = :token
      request.headers.merge! headers
    end

    context "if this is the first google sign in for the user" do
      it "creates the user based on the auth header" do
        expect { subject }.to change { User.count }.by(1)

        expect(User.exists?(email: email, provider: 'google')).to be true
      end
    end

    context "if the user already signed up with google" do
      let!(:user) { create :user, :provider_google, email: email }

      it "does not create a new database entry" do
        expect { subject }.to_not change { User.count }
      end
    end

    context 'if sign in was successful' do
      let(:response_body) { JSON.parse response.body }

      it 'returns the user data' do
        subject

        expect(response).to have_http_status :ok

        expect(response_body).to eq 'id' => User.last.id,
                                    'email' => 'test_user@test.com'
      end
    end
  end
end
