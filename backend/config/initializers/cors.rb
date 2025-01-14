Rails.application.config.middleware.insert_before 0, Rack::Cors do
  allow do
    origins '*'
    resource '*',
             headers: :any,
             expose: %w[access-token expired token-type uid client],
             methods: %i[get post options delete put]
  end
end
