class CreateDrawings < ActiveRecord::Migration[7.0]
  def change
    create_table :drawings do |t|
      t.string :title
      t.json :content

      t.timestamps
    end
  end
end
