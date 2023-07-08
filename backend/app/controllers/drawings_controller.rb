# frozen_string_literal: true

class DrawingsController < InternalApiController
  def index
    current_user

    @drawings = Drawing.all

    render react: {
      pageProps: {
        hello: "world",
      }
    }
  end

  def create
    Drawing.create! user: current_user,
                    title: params.require(:title),
                    content: params.require(:content)

    render json: {
      pageProps: {
        hello: "world",
      }
    }
  end
end
