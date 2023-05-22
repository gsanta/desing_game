class ArticlesController < ApplicationController
  def index
    render react: {
        hello: "world"
    }
  end
end
