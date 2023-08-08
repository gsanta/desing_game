

module ResponseHelper
  def respond_unauthorized(errors)
    respond_error(:unauthorized, errors)
  end

  def respond_error(status, errors)
    case errors
    when String
      render json: { error_msg: errors }, status: status
    end
  end
end
