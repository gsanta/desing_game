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
    CreateDrawing.new(create_drawing_attributes).execute
    render json: {
      pageProps: {
        hello: "world",
      }
    }
  end

  private

  def create_drawing_attributes
    params.require(:drawing).require([:content, :title])
    params.require(:drawing).permit([:content, :title])
  end
end
