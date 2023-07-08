require "rails_helper"
require_relative 'authenticated_and_authorized_action'
require_relative './helpers/examples_for_required_params'

RSpec.describe DrawingsController, type: :controller do
  let(:user) { create :user }

  describe "#index" do
    subject(:get_drawings) { get :index }

    it_behaves_like "an authenticated and authorized action for get"
  end

  describe "#create" do
    subject(:create_drawing) { get :create, params: params, as: :json }

    let(:title) { "Test drawing" }
    let(:content) { '{ "drawing": "content" }' }
    let(:params) { { title: title, content: content } }

    it_behaves_like "an authenticated and authorized action for post"

    context "when creating a new drawing" do
      before do
        sign_in user
      end

      it_behaves_like 'required parameter', param: :title

      it "should return 200:OK" do
        subject
        expect(response).to have_http_status(:success)
      end

      it "creates a drawing" do
        expect { subject }.to change(Drawing, :count).by 1
        expect(Drawing.last).to have_attributes user_id: user.id,
                                                title: title,
                                                content: content
      end
    end

  end
end
