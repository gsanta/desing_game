# frozen_string_literal: true

class ReactRenderer
  # module DSL
  #   extend ActiveSupport::Concern
  #
  #   def react
  #     @react ||= ReactRenderer.new(self)
  #   end
  #
  #   included { helper_method :react }
  # end
  #
  # module RSpec
  #   def rendered_react_props
  #     JSON.parse(controller.react.props)
  #   end
  # end

  attr_reader :props

  def initialize(controller)
    @controller = controller
  end

  def set_props(props)
    @props = props.to_json
  end

  def render(props)
    raise ArgumentError, 'react renderer requires a hash argument' if props.nil?
    set_props(props)
    { template: 'layouts/application_react', layout: false }
  end

  def pack_name
    "pages/#{controller_path}/#{action_name}"
  end

  delegate :controller_path, :action_name, to: :@controller, private: true
end
