<script lang="ts">
import { defineComponent } from 'vue';
import Query_Item from './Query_Item.vue';
import Query_Item_Selector from './Query_Item_Selector.vue';
import {Types} from '../../types'
    export default defineComponent ({
        data() {return {
            keys: ["name", "extention"], //Hardcoded for now, could be dynamaic
            selected: new Map
        }},
        emits:['delete'],
        components: {
            Query_Item,
            Query_Item_Selector
        },
        props: {
            name: String,
            value: String
        },
        created() {
            //Update keys with real values
        },
        methods: {
            addItem(key?:string, value?:string) {
                if (key != null && value != null) {
                    this.selected.set(key, value)
                }
            },
            submit() {
                let query:{}[] = []
                this.selected.forEach((value, key) => {
                    query.push({key: key, value: value})
                })
                console.log(query)
            }
        }
    })
</script>

<template>
    <Query_Item_Selector :options="keys" @submit="(key, value) => addItem(key, value)"/>
    <Query_Item v-for="item in selected" :name="item[0]" :value="item[1]" @delete="selected.delete(item[0])" />
    <div>
        <button @click="submit">Submit</button>
    </div>
</template>

<style>

</style>