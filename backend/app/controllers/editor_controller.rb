class EditorController < ApplicationController
  def index
    render react: {
        hello: "world"
    }
  end
end
